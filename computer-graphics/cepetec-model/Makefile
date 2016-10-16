# Variables
COMPILER = g++
LIBS     = -lglut -lSOIL -lGLU -lGL -lm
CFLAGS   = -g
NAME     = main
CLASSES  = camera.cpp latimmodel.cpp


all:
	$(COMPILER) -c camera.cpp $(LIBS) $(CFLAGS)
	$(COMPILER) -c latimmodel.cpp $(LIBS) $(CFLAGS)
	$(COMPILER) -c $(NAME).cpp $(LIBS) $(CFLAGS)
	$(COMPILER) -o $(NAME) $(NAME).o $(CLASSES) $(LIBS)
