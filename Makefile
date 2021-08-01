setup: setup.exec
			./setup.exec
setup.exec: main.cpp
			g++ main.cpp -o setup.exec
