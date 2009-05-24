MODULE := engine

MODULE_OBJS := \
	actor.o \
	bitmap.o \
	cmd_line.o \
	costume.o \
	font.o \
	gfx_opengl.o \
	gfx_tinygl.o \
	grim.o \
	keyframe.o \
	lab.o \
	lipsync.o \
	localize.o \
	lua.o \
	main.o \
	material.o \
	matrix3.o \
	matrix4.o \
	model.o \
	objectstate.o \
	primitives.o \
	registry.o \
	resource.o \
	savegame.o \
	scene.o \
	textobject.o \
	textsplit.o \
	version.o \
	walkplane.o

# Include common rules
include $(srcdir)/rules.mk