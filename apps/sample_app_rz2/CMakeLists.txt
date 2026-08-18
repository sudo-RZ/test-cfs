project(CFE_RZ2_APP C)

set(APP_SRC_FILES
  fsw/src/rz2_app.c
  fsw/src/rz2_app_cmds.c
  fsw/src/rz2_app_utils.c
)

if (CFE_EDS_ENABLED)
  list(APPEND APP_SRC_FILES
    fsw/src/rz2_app_eds_dispatch.c
  )
else()
  list(APPEND APP_SRC_FILES
    fsw/src/rz2_app_dispatch.c
  )
endif()

# Create the app module
#
# IMPORTANTE: el nombre pasado acá ("sample_app_rz2") tiene que ser el
# MISMO que el nombre de esta carpeta y el que se usa en cpu1_APPLIST
# (sample_defs/targets.cmake). El sistema de build de cFE resuelve a qué
# CPU pertenece cada tabla (add_cfe_tables, abajo) buscando ese nombre en
# una lista indexada por el nombre que aparece en cpu1_APPLIST; si acá se
# usa un nombre distinto (como pasaba antes con "rz2_app"), la tabla de
# ejemplo se compila pero nunca se instala/asocia a ningún CPU, la carga
# de la tabla falla al arrancar y la app termina llamando a
# CFE_ES_ExitApp() apenas se inicializa.
add_cfe_app(sample_app_rz2 ${APP_SRC_FILES})

target_include_directories(sample_app_rz2 PUBLIC fsw/inc)
# Include the public API from sample_lib to demonstrate how
# to call library-provided functions
add_cfe_app_dependency(sample_app_rz2 sample_lib)

# COMMS RZ1<->RZ2: acá SÍ hace falta declarar la dependencia de CMake.
# A diferencia de obc_hk/telecom (headers de mensaje simples), rz1_app usa
# el esqueleto completo de sample_app, cuyo rz1_app_msg.h arrastra
# rz1_app_mission_cfg.h -> rz1_app_interface_cfg.h, que NO es un header
# generado sino que vive en apps/sample_app_rz1/fsw/inc/ y solo es visible
# para quien dependa de ese target. add_cfe_app_dependency propaga esa
# carpeta de include (la que declaramos PUBLIC arriba en rz1) hacia acá.
add_cfe_app_dependency(sample_app_rz2 sample_app_rz1)

# Add table
add_cfe_tables(sample_app_rz2 fsw/tables/rz2_app_tbl.c)

# If UT is enabled, then add the tests from the subdirectory
# Note that this is an app, and therefore does not provide
# stub functions, as other entities would not typically make
# direct function calls into this application.
if (ENABLE_UNIT_TESTS)
  add_subdirectory(unit-test)
endif (ENABLE_UNIT_TESTS)
