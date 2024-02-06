target_sources(slae_lib
 	PUBLIC 
 		Matrix.cpp
 		LU_Decomposer.cpp
 		QR_Decomposer.cpp
 		Iteration_Method.cpp
		Power_Method.cpp
 )

target_include_directories(slae_lib PUBLIC ../headers)
