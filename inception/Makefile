all:
    mkdir -p ${HOME}/data/mysql ${HOME}/data/wordpress
    docker compose -f srcs/docker-compose.yml up --build -d

down:
	docker compose -f srcs/docker-compose.yml down

clean:
	docker compose -f srcs/docker-compose.yml down -v

fclean:clean
	docker system prune -af

re: fclean all