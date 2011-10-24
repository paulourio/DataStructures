# MAIN é o arquivo principal para ser chamado (sem a extensão do arquivo)
MAIN=exercicios

# Comando para remover arquivos
RM=rm -f

# Adiciona pastas aos diretórios de busca do LaTeX
export TEXINPUTS=$(shell kpsepath tex):$(shell pwd)/

# Padrão: gerar o PDF na pasta local
default: all

all: main

main: buildarvores $(MAIN) cleanout

buildarvores:
	cd arvores && cp ../Makefile . && make build_arvores_in
	rm arvores/Makefile
	
# Chamado de dentro da pasta arvores
build_arvores_in:
	find . -name '*tex' -exec pdflatex {\} \;
	find . -name '*pdf' -exec pdfcrop {\} {\} \;
	find . -name '*pdf' -exec pdf2svg {\} {\}.svg \;
	make cleanout

$(MAIN):
	pdflatex $(MAIN)
	pdflatex $(MAIN)

bibliografia:
	pdflatex $(MAIN)
	bibtex $(MAIN)

# Remover todos os arquivos gerados pelo LaTeX,
# exceto o PDF.
cleanout:
	$(RM) *.aux
	$(RM) *.bbl
	$(RM) *.blg
	$(RM) *.dvi
	$(RM) *.log
	$(RM) *.nav
	$(RM) *.out
	$(RM) *.snm
	$(RM) *.toc
	$(RM) *.vrb

# Chamado de dentro de arvore, para evitar recursividade
cleanoutput: cleanout
	$(RM) *.pdf

# Remover PDF e arquivos gerados pelo LaTeX.
clean: cleanout cleanoutput
	cd arvores && cp ../Makefile . && make cleanoutput && rm Makefile
