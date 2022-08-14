FROM gcc:4.9
COPY . /myapp
WORKDIR /myapp
RUN gcc -std=gnu11 signalfd.c -o signalfd
RUN gcc -std=gnu11 handler_sigqueue.c -o handler_sigqueue.c
RUN gcc -std=gnu11 sigqueue.c -o sigqueue
# CMD ["./signalfd"]