
make file generated by Autoconfig: dont edit

# build definitions
config = debug
compiler = gcc
system = linux
target_type = qt_plugin

# include general build instructions
include $(SHACIRADIR)/Targ/platforms/linux_gcc.defs

# include dependencies
-include linux_gcc_debug.dep

A_I_PATHS = \
	-I../../../Src/GUIFramework/QTFramework \
	-I../../../Src/GUIFramework/QTFramework/Keypads \
	-I/prj/qt3/include \
	-I/prj/qt3/makespecs/default
A_GEN_HEADERS =

A_L_PATHS = \
	-L"/prj/qt3/lib"
A_LIBS = \
	-lqt-mt
A_OBJECTS = \
	linux_gcc_debug/moc_qt_keyboard_button.o \
	linux_gcc_debug/moc_qt_keyboard_layout.o \
	linux_gcc_debug/qt_keyboard_button.o \
	linux_gcc_debug/qt_keyboard_layout.o \
	linux_gcc_debug/qt_plugin.o \
	linux_gcc_debug/qt_plugin_register.o
A_TARGETS = \
	linux_gcc_debug/moc_qt_keyboard_button.cpp \
	linux_gcc_debug/moc_qt_keyboard_layout.cpp \
	linux_gcc_debug/moc_qt_keyboard_button.o \
	linux_gcc_debug/moc_qt_keyboard_layout.o \
	linux_gcc_debug/qt_keyboard_button.o \
	linux_gcc_debug/qt_keyboard_layout.o \
	linux_gcc_debug/qt_plugin.o \
	linux_gcc_debug/qt_plugin_register.o

.PHONY: linux_gcc_debug all clean


dependencies:

clean:
	-rm $(A_TARGETS)

linux_gcc_debug/libKeypads.so: $(A_TARGETS)
	$(share)

$(QTDIR)/plugins/designer/libKeypads.so: linux_gcc_debug/libKeypads.so
	$(cp) $< $@

all: dependencies linux_gcc_debug $(A_TARGETS) $(QTDIR)/plugins/designer/libKeypads.so

linux_gcc_debug: linux_gcc_debug.mk
	$(mkdir) $@

linux_gcc_debug/moc_qt_keyboard_button.o: linux_gcc_debug/moc_qt_keyboard_button.cpp
	$(cpp)

linux_gcc_debug/moc_qt_keyboard_layout.o: linux_gcc_debug/moc_qt_keyboard_layout.cpp
	$(cpp)

linux_gcc_debug/qt_keyboard_button.o: ../../../Src/GUIFramework/QTFramework/Keypads/qt_keyboard_button.cpp
	$(cpp)

linux_gcc_debug/moc_qt_keyboard_button.cpp: ../../../Src/GUIFramework/QTFramework/Keypads/qt_keyboard_button.h
	$(QTDIR)/bin/moc ../../../Src/GUIFramework/QTFramework/Keypads/qt_keyboard_button.h -olinux_gcc_debug/moc_qt_keyboard_button.cpp

linux_gcc_debug/qt_keyboard_layout.o: ../../../Src/GUIFramework/QTFramework/Keypads/qt_keyboard_layout.cpp
	$(cpp)

linux_gcc_debug/moc_qt_keyboard_layout.cpp: ../../../Src/GUIFramework/QTFramework/Keypads/qt_keyboard_layout.h
	$(QTDIR)/bin/moc ../../../Src/GUIFramework/QTFramework/Keypads/qt_keyboard_layout.h -olinux_gcc_debug/moc_qt_keyboard_layout.cpp

linux_gcc_debug/qt_plugin.o: ../../../Src/GUIFramework/QTFramework/Keypads/Plugin/qt_plugin.cpp
	$(cpp)

linux_gcc_debug/qt_plugin_register.o: ../../../Src/GUIFramework/QTFramework/Keypads/Plugin/qt_plugin_register.cpp
	$(cpp)

