NAME = 2048
INPUT_FILE = Main.c

TEMPDIR = .temp/
SRCDIR = src/
BINDIR = bin/
TESTDIR = test/
RESDIR = ressources/

.DEFAULT_GOAL = help
.PHONY = help 

# Path where to search
VPATH = $(SRCDIR) $(TESTDIR) $(BINDIR)

# Affiche l'aide sur les commande de disponible dans le Makefile
help :	## Affiche l'aide
	@echo "Liste des sous-commandes disponible : " 
	@grep -E '(^[a-zA-Z_-]+ :.*?##.*$$)|(^##)' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf " >> \033[32m%-20s\033[0m %s\n", $$1, $$2}' | sed -e 's/\[32m##/[33m/'


SRC = $(wildcard $(SRCDIR)*.c)
SRC_OBJ = $(addprefix $(TEMPDIR), $(subst .c,.o, $(notdir $(SRC))))

# Compile tout les fichier necessaire pour l'execution de l'application
2048 : $(BINDIR) $(SRC_OBJ) ## Compile tout les fichiers
	@gcc -o $(BINDIR)$(NAME) $(SRCDIR)$(INPUT_FILE) #$(SRC_OBJ) currently useless in our case

# Compilation générique
$(TEMPDIR)%.o : %.c	$(TEMPDIR)
	@echo "Compiling $< ... "
	@gcc -o $@ -c $<

# Creation du dossier temporaire
$(TEMPDIR) :
	@echo "Creation dossier temporaire ..."
	@mkdir -p $(TEMPDIR)

$(BINDIR) :
	@echo "Creation dossier de sortie des binaires ..."
	@mkdir -p $(BINDIR)


# Install et compile tout les fichier necessaire pour l'execution de l'application
install : 2048 $(BINDIR) ## Installe l'application
	@echo "copying ressource files"
	@cp -r $(SRCDIR)$(RESDIR) $(BINDIR)


run : install ## lance l'application
	@$(OUTRELDIR)$(NAME)


TEST ?= $(wildcard $(TESTDIR)*Test.c)
TEST_OBJ = $(addprefix $(TEMPDIR),$(subst .c,.o, $(notdir $(TEST)) ))
TEST_EXEC = $(addprefix $(BINDIR)$(TESTDIR),$(subst .c,.out, $(notdir $(TEST))))

# Execute un code de test
test : $(TEST_EXEC) ## Lance les tests
	@for i in $(BINDIR)$(TESTDIR); do $$i; done

# Create and run tests 
$(BINDIR)$(TESTDIR)%.out : $(TEMPDIR)%.o $(BINDIR)$(TESTDIR)
	@gcc -o $@ $<

# Create directory for tests binaries
$(BINDIR)$(TESTDIR) :	
	@echo "Making directory $@"
	@mkdir -p $@
	

# Creer un ficher compresser contenant le projet
zip : ## Compresse le dossier
	@echo "Compression du dossier ..."
	@zip -r "Projet-Finale-"`date +%Y-%m-%d-%H-%M-%S` Makefile $(SRCDIR) $(BINDIR) $(TESTDIR) "Planificateur de projet.xlsx" "Compte Rendu.docx" Readme.md TODO.txt


# Efface le dossier temporaire
clean : ## Supprime les fichier temporaire
	@echo "Nettoyage du fichier temp/ et bin/test/"
	@rm -rf $(TEMPDIR)
	@rm -rf $(TESTDIR)$(BINDIR)


# Efface tout les fichie temporaire et compilé
mrproper : clean ## Supprime les fichier toute l'instalation
	@echo "Nettoyage complet"
	@rm -rf $(BINDIR)