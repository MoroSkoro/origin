FROM ubuntu:16.04
	RUN apt-get update && apt-get install -y g++ nano net-tools inetutils-ping
	WORKDIR /root/task1/
	COPY Task_1/hello_world.cpp .
	RUN g++ hello_world.cpp -o hello_world
	CMD ["./hello_world"]