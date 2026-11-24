#ifndef RAGNAROK_SOURCE_UI_ITEMS_UIEQUIPWND_H
#define RAGNAROK_SOURCE_UI_ITEMS_UIEQUIPWND_H

#include "UI/Window/UIFrameWnd.h"

struct EquipWndInfo;
struct ITEM_INFO;
class UITabControl;
class UIListBoxTitle;
class UIBitmapButton;
class UICheckBox;

class UISwapEquipmentWnd;
class UIScrollBar;

struct AffinityVisualSettings {
  int panelHeight = 36;
  bool centered = true;
  int x = 0;
  int y = 149;
  int stepX = 28;
  int stepY = 0;
  int width = 24;
  int height = 24;
  bool drawBackground = true;
  int backgroundX = 1;
  int backgroundY = 147;
  int backgroundWidth = 0;
  int backgroundHeight = 34;
  unsigned int backgroundColor = 0xFFFFFF;
  int iconX = 0;
  int iconY = 0;
  std::string slotImage;
  std::string lockedImage;
  std::string lockOverlay;
  std::string highlightImage;
  std::string panelImage;
  bool customPosition[6] = {};
  int slotX[6] = {};
  int slotY[6] = {};
};

class UIEquipWnd : public UIFrameWnd {
public:
  UIEquipWnd();
  bool NeedsFrameRefresh() override;
  void Move(int x, int y) override;
  void DragAndDrop(int x, int y, std::intptr_t value) override;
  void StoreInfo() override;
  void Paint() override;
  void OnCreate(int width, int height) override;
  /* 00B4 */ int m_viewOther;
  /* 00B8 */ int m_highlight[3];
  /* 00C4 */ int m_show;
  /* 00C8 */ EquipWndInfo* m_placement;
  /* 00CC */ UIBitmapButton* m_viewButton;
  /* 00D0 */ UIBitmapButton* m_otherButton;
  /* 00D4 */ std::uint32_t m_updateTick;
  /* 00D8 */ int contentOffset;
  /* 00DC */ UICheckBox* allowViewCheck;
  /* 00E0 */ UICheckBox* swapModeCheck;
  /* 00E4 */ unsigned char padding_00E4[0x08];
  /* 00EC */ UITabControl* m_tabs;
  /* 00F0 */ int m_page;
  /* 00F4 */ int m_contentTop;
  /* 00F8 */ int appearance[8];
  /* 0118 */ int robeId;
  /* 011C */ int costumeJob;
  /* 0120 */ UIListBoxTitle* m_titleList;
  /* 0124 */ UISwapEquipmentWnd* swapWindow;
  /* 0128 */ int swapState;
  /* 012C */ UIBitmapButton* swapButton;
  /* 0130 */ UIBitmapButton* unequipButton;
  /* 0134 */ UIScrollBar* m_scrollBar;
  /* 0138 */ UIWindow* damageSkinButtons[6];
  /* 0150 */ int padding_0150;
  /* 0154 */ int m_firstSlot;
  /* 0158 */ int m_hoverSlot;
  /* 015C */ int damageSkinMode;
  /* 0160 */ std::vector<std::string> m_damageSkinNames;
  /* 016C */ std::vector<std::string> m_damageSkinIcons;
  /* 0178 */ UIBitmapButton* abilityButton;
  AffinityVisualSettings affinityVisual;

  void OnProcess() override;
  void OnLBtnDown(int x, int y) override;
  void OnLBtnDblClk(int x, int y) override;
  void OnMouseMove(int x, int y) override;
  void OnMouseHover(int x, int y) override;
  void OnLBtnUp(int x, int y) override;
  void OnRBtnDown(int x, int y) override;
  void OnWheel(int delta) override;
  int SendMsg(UIWindow* sender, int message, std::intptr_t a, std::intptr_t b, std::intptr_t c, std::intptr_t d) override;

  void DrawDamageSkinPage();
  void DrawEquipSlots();
  void LoadAffinityVisualSettings();
  void AffinitySlotPosition(int slot, int& x, int& y) const;
  int AffinityPanelHeight() const;
  int AffinitySlotAt(int x, int y) const;
  void RefreshAffinityLayout();
  void DrawAffinitySlots();
  void RefreshTitleList();
  void NotifyEquipmentChanged();
  void UpdateCharacterView(int reset);
  void RefreshLook();
  ITEM_INFO GetSlotItem(int slot);
  ITEM_INFO ItemIconAt(int x, int y);
  ITEM_INFO ItemEntryAt(int x, int y);
};

#endif
