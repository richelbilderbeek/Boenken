#!/usr/bin/env python3
"""Play the WebAssembly game on the 'Play' page of a built website.

Usage: test_play_page.py <URL of the play page>

The game must show the menu without a title bar,
clicking 'Start game' must start a game,
pressing a key of the red player must make it move
and pressing Escape must go back to the menu.
"""
import io
import sys
import time

from PIL import Image, ImageChops, ImageStat
from playwright.sync_api import sync_playwright

START_TIMEOUT_SECS = 60
# The menu dialog has a gradient from #FF9090 (top-left) to #9090FF,
# see qtmain.cpp
MENU_TOP_LEFT = (0xFF, 0x90, 0x90)
# The arena is black, see qtboenkenmaindialog.cpp
ARENA_COLOR = (1, 1, 1)
# Where the 'Start game' button is, see qtboenkenmenudialog.ui
START_BUTTON = (164, 257)
# The default arena size is 640x400, see qtboenkenarenadialog.ui
ARENA_BOX = (0, 0, 640, 400)
MAX_COLOR_DIFF = 40  # Sum of the differences per color channel
MIN_MOVE_DIFF = 0.01  # Average difference per color channel, from 0 to 255


def color_diff(color_a, color_b):
    """Sum of the differences per color channel."""
    return sum(abs(a - b) for a, b in zip(color_a, color_b))


def diff(image_a, image_b):
    """Average difference per color channel between two images."""
    stat = ImageStat.Stat(ImageChops.difference(image_a, image_b))
    return sum(stat.mean) / len(stat.mean)


def main():
    url = sys.argv[1]
    errors = []
    with sync_playwright() as playwright:
        browser = playwright.chromium.launch()
        page = browser.new_page(viewport={"width": 1280, "height": 1300})
        page.on("pageerror", lambda error: errors.append(str(error)))
        page.on("console", lambda m: print(f"console: {m.text}"))
        page.goto(url)
        frame = page.locator("iframe")

        def screenshot():
            data = frame.screenshot()
            return Image.open(io.BytesIO(data)).convert("RGB")

        def top_left():
            return screenshot().getpixel((5, 5))

        def wait_for(color, what):
            deadline = time.time() + START_TIMEOUT_SECS
            pixel = top_left()
            while (time.time() < deadline
                   and color_diff(pixel, color) > MAX_COLOR_DIFF):
                print(f"Waiting for {what}, top-left pixel: {pixel}")
                time.sleep(1)
                pixel = top_left()
            assert color_diff(pixel, color) <= MAX_COLOR_DIFF, \
                f"No {what} shown at the top-left, but {pixel}"

        wait_for(MENU_TOP_LEFT, "the menu")
        assert not errors, errors

        print("Clicking 'Start game'")
        frame.click(position={"x": START_BUTTON[0], "y": START_BUTTON[1]})
        wait_for(ARENA_COLOR, "the arena")

        # Nothing moves before a player moves
        time.sleep(2)
        before = screenshot().crop(ARENA_BOX)
        print("Pressing 'W' to make the red player move")
        for _ in range(10):
            page.keyboard.press("w")
            time.sleep(0.05)
        time.sleep(1)
        after = screenshot().crop(ARENA_BOX)
        move_diff = diff(before, after)
        print(f"Difference after moving: {move_diff:.3f}")
        assert move_diff > MIN_MOVE_DIFF, "Red player did not move"

        print("Pressing Escape to go back to the menu")
        page.keyboard.press("Escape")
        wait_for(MENU_TOP_LEFT, "the menu")
        assert not errors, errors
        browser.close()
    print("OK: the game can be played")


if __name__ == "__main__":
    main()
