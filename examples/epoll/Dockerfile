FROM gcc:4.9
COPY . /myapp
WORKDIR /myapp
RUN gcc -pthread -std=gnu11 main.c epoll_read_fds_vector.c -o main
CMD ["./main"]