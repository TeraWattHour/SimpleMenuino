#ifndef SIMPLEMENU_H
#define SIMPLEMENU_H

typedef struct {
  char *name;
  size_t nameSize;
  void (*handler)();
} Item;

class Menu {
private:
  size_t mHeight;
  size_t mWidth;

  int mShift = 0;
  long long mLastShiftedAt;
  int mAutoScrollDelay = 500;

  size_t mItemsCount = 0;
  Item *mItems = NULL;

  char *mCurrentLine;
  char *mCurrentFrame;
  int mFrameSize;

public:
  // Current cursor/selected item position.
  int position = 0;

  // Constructs a `Menu` object.
  // This constructor needs to be used by every derived class.
  Menu(size_t lcdWidth, size_t lcdHeight, int autoScrollDelay = 500);

  // Registers an item with a name and associates it with its handler.
  int registerItem(char *name, void (*handler)());

  // Renames an item without changing its handler or position.
  int renameItem(int index, char *newName);

  // Sets the cursor to some position.
  int setPosition(int newPosition);

  // Call this method if you want to click/select a focused item.
  int select();

  // This method handles printing of the menu.
  // It doesn't use delay().
  int handler();

  // This function will be called every time any menu item is selected.
  // Needs to be implemented on every derived class.
  virtual void handleSelected(int position);

  // A bridge between your display and the `Menu` class.
  // Needs to be implemented on every derived class.
  virtual void setCursor(int x, int y);

  // A bridge between your display and the `Menu` class.
  // Needs to be implemented on every derived class.
  virtual void print(char *text);
};

#endif