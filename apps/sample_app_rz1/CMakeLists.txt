project(CFE_RZ1_APP C)

set(APP_SRC_FILES
  fsw/src/rz1_app.c
  fsw/src/rz1_app_cmds.c
  fsw/src/rz1_app_utils.c
)

if (CFE_EDS_ENABLED)
  list(APPEND APP_SRC_FILES
    fsw/src/rz1_app_eds_dispatch.c
  )
else()
  list(APPEND APP_SRC_FILES
    fsw/src/rz1_app_dispatch.c
  )
endif()

# Create the app module
#
# IMPORTANTE: el nombre pasado acá ("sample_app_rz1") tiene que ser el
# MISMO que el nombre de esta carpeta y el que se usa en cpu1_APPLIST
# (sample_defs/targets.cmake). El sistema de build de cFE resuelve a qué
# CPU pertenece cada tabla (add_cfe_tables, abajo) buscando ese nombre en
# una lista indexada por el nombre que aparece en cpu1_APPLIST; si acá se
# usa un nombre distinto (como pasaba antes con "rz1_app"), la tabla de
# ejemplo se compila pero nunca se instala/asocia a ningún CPU, la carga
# de la tabla falla al arrancar y la app termina llamando a
# CFE_ES_ExitApp() apenas se inicializa.
add_cfe_app(sample_app_rz1 ${APP_SRC_FILES})

target_include_directories(sample_app_rz1 PUBLIC fsw/inc)
# Include the public API from sample_lib to demonstrate how
# to call library-provided functions
add_cfe_app_dependency(sample_app_rz1 sample_lib)

# COMMS RZ1<->RZ2: RZ1 recibe el mensaje que publica RZ2 (rz1_app_cmds.h
# incluye "rz2_app_msg.h"), así que necesita la carpeta fsw/inc de RZ2
# (rz2_app_interface_cfg.h no es un header generado). Mismo motivo por el
# que sample_app_rz2 depende de sample_app_rz1 más abajo en su CMakeLists.
add_cfe_app_dependency(sample_app_rz1 sample_app_rz2)

# Add table
add_cfe_tables(sample_app_rz1 fsw/tables/rz1_app_tbl.c)

# If UT is enabled, then add the tests from the subdirectory
# Note that this is an app, and therefore does not provide
# stub functions, as other entities would not typically make
# direct function calls into this application.
if (ENABLE_UNIT_TESTS)
  add_subdirectory(unit-test)
endif (ENABLE_UNIT_TESTS)
