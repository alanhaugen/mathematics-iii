all: report1.pdf

%.pdf: %.md
	pandoc --pdf-engine=xelatex $< -o $@
