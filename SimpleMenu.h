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
  int position = 0;
  Menu(size_t lcdWidth, size_t lcdHeight, int autoScrollDelay = 500);
  
  int renameItem(int index, char *newName);
  int registerItem(char *name, void (*handler)());
  int setPosition(int newPosition);
  int select();
  int handler();

  virtual void handleSelected(int position);
  virtual void setCursor(int x, int y);
  virtual void print(char *text);
};

#endif