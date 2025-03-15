CC = c++
OPT = -std=c++14 -O3

# set main here
MAIN = stack_n_heap.c

##################################################################################################################
TARGETDIR   := bin

all: $(TARGETDIR)/stack_n_heap

debug: OPT += -DDEBUG -g
debug: all

$(TARGETDIR)/stack_n_heap: ${MAIN}
	@mkdir -p $(@D)
	$(CC) $^ -o $@ $(OPT)

clean:
	rm -r $(TARGETDIR)/
