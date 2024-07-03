NAME = ircserv
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

# Répertoires des sources et objets
SRCDIR = ./src
OBJDIR = ./obj

# Répertoire des sources dans le sous-répertoire Commands
COMMANDSDIR = $(SRCDIR)/Commands

# Liste des fichiers source dans le répertoire principal
SRC_MAIN = $(SRCDIR)/main.cpp \
	$(SRCDIR)/Channel.cpp \
	$(SRCDIR)/Client.cpp \
	$(SRCDIR)/handleClientEvents.cpp \
	$(SRCDIR)/HandleCommandEvents.cpp \
	$(SRCDIR)/Parsing.cpp \
	$(SRCDIR)/PrintFunctions.cpp \
	$(SRCDIR)/Server.cpp \
	$(SRCDIR)/utils.cpp \
	$(SRCDIR)/Welcome.cpp \

# Liste des fichiers source dans le répertoire Commands
SRC_COMMANDS = $(COMMANDSDIR)/User.cpp \
	$(COMMANDSDIR)/Invite.cpp \
	$(COMMANDSDIR)/Join.cpp \
	$(COMMANDSDIR)/Kick.cpp \
	$(COMMANDSDIR)/Mode.cpp \
	$(COMMANDSDIR)/Nick.cpp \
	$(COMMANDSDIR)/Oper.cpp \
	$(COMMANDSDIR)/Part.cpp \
	$(COMMANDSDIR)/Pass.cpp \
	$(COMMANDSDIR)/Ping.cpp \
	$(COMMANDSDIR)/Privmsg.cpp \
	$(COMMANDSDIR)/Quit.cpp \
	$(COMMANDSDIR)/Topic.cpp \
	$(COMMANDSDIR)/Unknown.cpp \

# Concaténer les listes de fichiers source
SRC = $(SRC_MAIN) $(SRC_COMMANDS)

# Déduire les noms des fichiers objets
OBJ = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))

# Créer le répertoire obj s'il n'existe pas
$(shell mkdir -p $(OBJDIR) $(OBJDIR)/Commands)

# Règle pour compiler chaque fichier source en fichier objet individuel
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Règle pour construire l'exécutable
$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

all: $(NAME)

# Cible pour nettoyer les fichiers objets
clean:
	rm -rf $(OBJ)

# Cible pour nettoyer les fichiers objets et l'exécutable
fclean: clean
	rm -rf $(NAME)

# Cible par défaut pour tout reconstruire
re: fclean all

.PHONY: all clean fclean re
