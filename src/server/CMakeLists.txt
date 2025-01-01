PROJECT(server)
ADD_EXECUTABLE(${PROJECT_NAME}
	main.cpp
	server.cpp			server.h
	session.cpp			session.h
	../utils.cpp		../utils.h
)
