all: up

up:
	mkdir -p /home/tvan-bee/data/wordpress
	mkdir -p /home/tvan-bee/data/mariadb
	docker-compose -f srcs/docker-compose.yml up -d

down:
	docker-compose -f srcs/docker-compose.yml down

clean:
	rm -rf /home/tvan-bee/data
