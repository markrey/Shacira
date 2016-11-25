// ==========================================================================
// qt_keyboard_button.cpp
//
// Implementierung fuer cQtKeyboardButton
// ==========================================================================

#include "cQtKeyboardButton.h"
#include "cQtKeyboardLayout.h"


// ---------------------------------------------------------------------------
// cQtKeyboardButton in Qt Designer Plugin einbinden
// QT_PLUGIN_REGISTER(class_name, include_file, icon_set, group, tool_tip, whats_this, is_container)
// ---------------------------------------------------------------------------

#ifdef _KEYPAD_PLUGIN_
#include "cQtPluginRegistry.h"
QT_PLUGIN_REGISTER(cQtKeyboardButton, "cQtKeyboardButton.h", DEFAULT_ICON, "Keypads", 0, 0, false)
#endif

// ---------------------------------------------------------------------------
// Implementierung fuer cQtKeyboardButton
// ---------------------------------------------------------------------------

cQtKeyboardButton::cQtKeyboardButton( QWidget *parent, const char *name) : 
   QPushButton(parent, name) 
{
   // selbstdefinierte Properties
   setKeyFont( fontSmallFont );
   setKeyType( typeNormal );
   setKeyHeightX10( 10 );
   setKeyWidthX10( 10 );

   // Properties von QPushButton anpassen
   // setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding); 

   // signal & slot Verbindungen: clicked() und toggled(bool) von QPushButton
   // werden um cQtKeyboardButton* ergaenzt an cQtKeyboardLayout geschickt.
   connect( this, SIGNAL( clicked() ), 
            this, SLOT( slotClicked() ) );
   connect( this, SIGNAL( toggled(bool) ), 
            this, SLOT( slotToggled(bool) ) );

   QObject *layout = parent;
   //while ((layout != 0) && (layout->className() != "cQtKeyboardLayout")) {
   while ((layout != 0) && (layout->inherits("cQtKeyboardLayout") == false)) {
      layout = layout->parent();
   }

   if (layout != 0) {
      // nur wenn der Button auch in ein Layout eingebettet ist
      connect( this, SIGNAL( clicked(cQtKeyboardButton*) ), 
               layout, SLOT( slotClicked(cQtKeyboardButton*) ) );
      connect( this, SIGNAL( toggled(cQtKeyboardButton*, bool) ), 
               layout, SLOT( slotToggled(cQtKeyboardButton*, bool) ) );
   }

   /*
   if (this->parent()->className() == "cQtKeyboardLayout") {
      // nur wenn der Button auch in ein Layout eingebettet ist
      cQtKeyboardLayout *layout = (cQtKeyboardLayout*)this->parent();
      connect( this, SIGNAL( clicked(cQtKeyboardButton*) ), 
               layout, SLOT( slotClicked(cQtKeyboardButton*) ) );
      connect( this, SIGNAL( toggled(cQtKeyboardButton*, bool) ), 
               layout, SLOT( slotToggled(cQtKeyboardButton*, bool) ) );
   } else {
      QString check1 = this->parent()->className();
      QString check2 = parent->className();
   }
   */
}


/**
 * Der Qt Designer unterst�tzt Zeilenumbr�che in der Button-Beschriftung nur
 * eingeschr�nkt (werden fehlerhaft gespeichert/geladen). Da mehrzeilige
 * Beschriftungen aber ben�tigt werden, wurde diese Methode �berladen
 * um zur Laufzeit in Klartext eingef�gte "\\n" (2 Zeichen) durch ein
 * '\\n' (1 Zeichen) zu ersetzen. 
 */
void cQtKeyboardButton::setText(const QString &t)
{ 
   QString tt = t;
#ifndef QT_PLUGIN
   // Nicht im Plugin selbst, sonst w�rde es rausgefiltert werden!
   tt.replace("\\n","\n");
#endif
   QPushButton::setText(tt);
}


/**
 * Wenn der Button in ein cQtKeyboardLayout eingebettet ist, kann mit dieser
 * Funktion einer der Referenzfonts gew�hlt werden.
 * Steht im Designer als Property zur Verf�gung. Blabla.
 */
void cQtKeyboardButton::setKeyFont(KEY_FONT kf) 
{ 
   _key_font = kf;

   QObject *layout = parent();
   while ((layout != 0) && (!layout->inherits("cQtKeyboardLayout"))) {
      layout = layout->parent();
   }
   if (layout) {
      // nur wenn der Button auch in ein Layout eingebettet ist
      switch (_key_font) {
      case fontSmallFont:
         setFont(((cQtKeyboardLayout*)layout)->getSmallFont());
         break;
      case fontBigFont:
         setFont(((cQtKeyboardLayout*)layout)->getBigFont());
         break;
      case fontManual:
      default:
         // kein Font von Layout uebernehmen
         break;
      }
   }
}


/**
 * Berechnet aus Raster (cQtKeyboardLayout) und
 * Multiplikatoren (cQtKeyboardButton) die aktuelle Buttongr��e.
 */
QSize cQtKeyboardButton::sizeHint() const 
{
   int w = 40;
   int h = 40;

   QObject *layout = parent();
   while ((layout != 0) && (!layout->inherits("cQtKeyboardLayout"))) {
      layout = layout->parent();
   }
   if (layout) {
      // nur wenn der Button auch in ein Layout eingebettet ist
      w = ((cQtKeyboardLayout*)layout)->getKeyWidth();
      h = ((cQtKeyboardLayout*)layout)->getKeyHeight();
   }

   return QSize( w * _key_width_x10 / 10, h * _key_height_x10 / 10 );
}

