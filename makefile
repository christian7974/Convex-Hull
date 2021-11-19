OBJS = Convex_Hull_Final_Program.o
CXX = g++
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

game: $(OBJS)
	$(CXX) -o game $(OBJS) $(LDLIBS)

clean:
	$(RM) game $(OBJS)