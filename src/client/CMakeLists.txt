PROJECT(client)
ADD_EXECUTABLE(${PROJECT_NAME}
	main.cpp
	client.cpp			client.h
	../session.cpp		../session.h
	../utils.cpp		../utils.h
)
