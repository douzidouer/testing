# makefile 

objs   := main.o mfi.o server.o
target := mfi

# Creating the target
$(target): $(objs)
	gcc -Wall -o $@ $^ -l bcm2835 

# Creating the dependance
%.o: %.c 
	gcc -Wall -c -o $@ $< -D DEBUG


.PHONY: clean
clean:
	-rm -f $(objs) $(target)