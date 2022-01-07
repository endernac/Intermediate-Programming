# Andrew Cornelio & Vivek Gopalakrishnan
# acornel9 & vgopala4

CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra -g

project: project.o ppm_io.o image_manip.o
	$(CC) project.o ppm_io.o image_manip.o -o project -lm

project.o: project.c ppm_io.h
	$(CC) $(CFLAGS) -c project.c

image_manip.o: image_manip.c image_manip.h ppm_io.h
	$(CC) $(CFLAGS) -c image_manip.c

ppm_io.o: ppm_io.c ppm_io.h
	$(CC) $(CFLAGS) -c ppm_io.c

clean:
	rm -f *.o *.ppm project
