
#include "CListView.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "cQtPluginRegistry.h"
#include "plugin_icons.h"
SH_PLUGIN_REGISTER(ViewWidget, \
                   CListView, \
                   ICON_SET("designer_listview"), \
                   "list view widget")
#endif

#include <qimage.h>

static const unsigned char height24_data[] = { 
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x18,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x3b, 0xcc, 0x97, 0xda, 0x00, 0x00, 0x00,
    0x0c, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0x63, 0x60, 0x18, 0x18, 0x00,
    0x00, 0x00, 0x78, 0x00, 0x01, 0x0b, 0xce, 0xbd, 0x08, 0x00, 0x00, 0x00,
    0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};

static const unsigned char height32_data[] = { 
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x20,
    0x08, 0x06, 0x00, 0x00, 0x00, 0xd3, 0xe5, 0x12, 0x1a, 0x00, 0x00, 0x00,
    0x0c, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0x63, 0x60, 0x18, 0xdc, 0x00,
    0x00, 0x00, 0xa0, 0x00, 0x01, 0xb0, 0x06, 0x62, 0x18, 0x00, 0x00, 0x00,
    0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};

static const unsigned char height40_data[] = { 
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x28,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x3f, 0xb6, 0x90, 0x77, 0x00, 0x00, 0x00,
    0x0c, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0x63, 0x60, 0x18, 0x1e, 0x00,
    0x00, 0x00, 0xc8, 0x00, 0x01, 0xad, 0x40, 0x76, 0x22, 0x00, 0x00, 0x00,
    0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};

static const unsigned char height48_data[] = { 
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x30,
    0x08, 0x06, 0x00, 0x00, 0x00, 0xd0, 0x33, 0x10, 0x81, 0x00, 0x00, 0x00,
    0x0c, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0x63, 0x60, 0x18, 0x59, 0x00,
    0x00, 0x00, 0xf0, 0x00, 0x01, 0x06, 0x94, 0x89, 0xfd, 0x00, 0x00, 0x00,
    0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};

CListView::CListView(QWidget * parent, const char * name, WFlags f)
   : QListView(parent, name),
     CWidgetBase(this)
{
   CONSTRUCT_WIDGET

   _VarRef = NULL;
   _VarView = NULL;
   if (TOUCH_SCREEN_ACTIVE()) {
      _ItemHeightValue = Height40;
   } else {
      _ItemHeightValue = NormalHeight;
   }
}

CListView::~CListView() 
{
}

void CListView::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QListView::mousePressEvent(e);
   }
}

void CListView::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QListView::mouseReleaseEvent(e);
   }
}


// GUI related virtual methods

void CListView::View()
{
}

void CListView::DelayedLanguageChange()
{
}

// CCS related virtual methods

void CListView::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CCSInitializeVarRef(_VarSpec, _VarRef, _VarView, 0);
WMETHOD_VOID_EPILOG
#endif
}

void CListView::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
#endif
}

void CListView::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
#endif
}

void CListView::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
#ifndef QT_PLUGIN
#endif
}

void CListView::AdjustItemHeight(QListViewItem * item)
{
   if (_ItemHeightValue == NormalHeight) {
      return;
   }
   QPixmap pixmap;
   if (_ItemHeightValue == Height24) {
      pixmap.loadFromData(height24_data, sizeof(height24_data), "PNG" );
   } else if (_ItemHeightValue == Height32) {
      pixmap.loadFromData(height32_data, sizeof(height32_data), "PNG" );
   } else if (_ItemHeightValue == Height40) {
      pixmap.loadFromData(height40_data, sizeof(height40_data), "PNG" );
   } else if (_ItemHeightValue == Height48) {
      pixmap.loadFromData(height48_data, sizeof(height48_data), "PNG" );
   } else {
      return;
   }
   if (item != NULL) {
      SetImage(item, pixmap);
   } else {
      QListViewItemIterator it(this);
      QListViewItem * current_item = it.current();
      while (current_item != NULL) {
         SetImage(current_item, pixmap);
         it++;
         current_item = it.current();
      }
   }
}

void CListView::SetImage(QListViewItem * item, QPixmap & pixmap)
{
   item->setPixmap(0, pixmap);
}
