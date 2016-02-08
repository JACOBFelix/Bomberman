NAME		= 	bomberman

DIR		=	src

COMP		=	$(DIR)/Components
SYST		=	$(DIR)/Systems
TEST		=	test

SRC		+=	$(DIR)/ASystem.cpp
SRC		+=	$(DIR)/AMutex.cpp
SRC		+=	$(DIR)/ANetwork.cpp
SRC		+=	$(DIR)/AThread.cpp
SRC		+=  	$(DIR)/BaseComponent.cpp
SRC		+=  	$(DIR)/Client.cpp
SRC		+=	$(DIR)/Cube.cpp
SRC		+=	$(DIR)/Display.cpp
SRC		+=  	$(DIR)/Exceptions.cpp
SRC		+=	$(DIR)/Engine.cpp
SRC		+=	$(DIR)/Entity.cpp
SRC		+=	$(DIR)/Export.cpp
SRC		+=	$(DIR)/FactoryComponent.cpp
SRC		+=	$(DIR)/FactoryEntity.cpp
SRC		+=  	$(DIR)/main.cpp
SRC		+=  	$(DIR)/Mutex.cpp
SRC		+=  	$(DIR)/ScopeLock.cpp
SRC		+=  	$(DIR)/Server.cpp

SRC		+=	$(COMP)/Bonus.cpp
SRC		+=	$(COMP)/Breakable.cpp
SRC		+=	$(COMP)/Fd.cpp
SRC		+=	$(COMP)/Id.cpp
SRC		+=	$(COMP)/InputContext.cpp
SRC		+=	$(COMP)/IsAI.cpp
SRC		+=	$(COMP)/Model.cpp
SRC		+=	$(COMP)/Move.cpp
SRC		+=	$(COMP)/NbBomb.cpp
SRC		+=	$(COMP)/PlayerInfo.cpp
SRC		+=	$(COMP)/Position.cpp
SRC		+=	$(COMP)/Range.cpp
SRC		+=	$(COMP)/Solid.cpp
SRC		+=	$(COMP)/Timer.cpp

SRC		+=	$(SYST)/AI.cpp
SRC		+=	$(SYST)/Bomb.cpp
SRC		+=	$(SYST)/Draw.cpp
SRC		+=	$(SYST)/Input.cpp
SRC		+=	$(SYST)/Move.cpp

OBJ		=	$(SRC:.cpp=.o)

CXXFLAGS	+= 	-W -Wall -Wextra
CXXFLAGS	+= 	-I includes
CXXFLAGS	+= 	-I includes/Components
CXXFLAGS	+=	-I lib/includes
CXXFLAGS	+= 	-I interfaces
CXXFLAGS	+=	-I abstract
CXXFLAGS	+= 	-std=c++11

LDXXFLAGS 	+=	-Llib/libs
LDXXFLAGS	+=	-lgdl_gl
LDXXFLAGS	+=	-lGL
LDXXFLAGS	+=	-lGLU
LDXXFLAGS	+=	-lGLEW
LDXXFLAGS	+=	-ldl
LDXXFLAGS	+=	-lrt
LDXXFLAGS	+=	-lSDL2
LDXXFLAGS	+=	-lpthread
LDXXFLAGS	+=	-lSDL
LDXXFLAGS 	+= 	-lfbxsdk

RM		= 	rm -f

CC		= 	g++

%.o: %.cpp
		@$(CC) -c -o $@ $<  $(CXXFLAGS)
		@printf "[\033[0;32mcompiled\033[0m] % 39s\n" $< | sed "s/ /./2g"

all:		$(NAME)

$(NAME):	$(OBJ)
		@$(CC) $(OBJ) -o $(NAME) $(LDXXFLAGS)
		@printf "[\033[0;36mbuilt\033[0m] % 42s\n" $(NAME) | sed "s/ /./5g"

clean:
		@$(RM) $(OBJ)
		@printf "[\033[0;31mdeleted\033[0m] % 40s\n" $(OBJ) | sed "s/ /./3g"

fclean:		clean
		@$(RM) $(NAME)
		@printf "[\033[0;35mdeleted\033[0m] % 40s\n" $(NAME) | sed "s/ /./3g"

re:		fclean all

.PHONY:		all clean fclean re
