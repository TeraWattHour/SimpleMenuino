#include <Arduino.h>
#include "SimpleMenu.h"

Menu::Menu(size_t lcdWidth, size_t lcdHeight, int autoScrollDelay = 500) {
  mWidth = lcdWidth;
  mHeight = lcdHeight;
  mFrameSize = lcdWidth - 4;
  mAutoScrollDelay = autoScrollDelay;

  mCurrentLine = malloc((mWidth + 1) * sizeof(char));
  mCurrentLine[mWidth] = '\0';

  mCurrentFrame = malloc((mFrameSize + 1) * sizeof(char));
  mCurrentFrame[mFrameSize] = '\0';
}

int Menu::registerItem(char *name, void (*handler)()) {
  Item newItem = {
    .name = name,
    .nameSize = strlen(name),
    .handler = handler,
  };
  mItems = realloc(mItems, (mItemsCount + 1) * sizeof(Item));
  mItems[mItemsCount] = newItem;

  mItemsCount++;
}

int Menu::renameItem(int index, char *newName) {
  if (index >= mItemsCount) {
    return 1;
  }
  mItems[index].name = newName;
  mItems[index].nameSize = strlen(newName);
}

int Menu::setPosition(int newPosition) {
  mShift = 0;
  mLastShiftedAt = millis();

  if (newPosition < 0) {
    position = mItemsCount - 1;
    return;
  }

  position = newPosition % mItemsCount;
}

int Menu::select() {
  handleSelected(this->position);
  mItems[position].handler();
}

int Menu::handler() {
  if (millis() - mLastShiftedAt >= mAutoScrollDelay) {
    mShift += 1;
    mLastShiftedAt = millis();
  }

  int frame = position / mHeight;
  int row = position % mHeight;

  for (int y = 0; y < mHeight; ++y) {
    for (int x = 0; x < mWidth; ++x) {
      mCurrentLine[x] = ' ';
    }

    int currentPosition = (frame * mHeight) + y;

    if (currentPosition < mItemsCount) {
      bool isFocus = currentPosition == position;

      auto item = mItems[currentPosition];
      char *name = item.name;
      size_t nameSize = item.nameSize;

      mCurrentFrame[mFrameSize] = '\0';
      for (int i = 0; i < mFrameSize; ++i) {
        mCurrentFrame[i] = ' ';
      }

      for (int i = 0; i < nameSize && i < mFrameSize; ++i) {
        mCurrentFrame[i] = name[isFocus && mAutoScrollDelay > 0 && mFrameSize < nameSize ? (i + mShift) % nameSize : i];
      }

      sprintf(mCurrentLine, "%c %s %c", isFocus ? '>' : ' ', mCurrentFrame, isFocus ? '<' : ' ');
    }

    setCursor(0, y);
    print(mCurrentLine);
  }
}