# ----------------------------
# Makefile Options
# ----------------------------

NAME = cplxmat
ICON = icon.png
DESCRIPTION = "Allows you to create and manipulate complex matricies."
COMPRESSED = NO
ARCHIVED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
