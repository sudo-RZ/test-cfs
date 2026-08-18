###########################################################
#
# RZ2_APP platform build setup
#
# This file is evaluated as part of the "prepare" stage
# and can be used to set up prerequisites for the build,
# such as generating header files
#
###########################################################

# The list of header files that control the RZ2_APP configuration
set(RZ2_APP_PLATFORM_CONFIG_FILE_LIST
  rz2_app_internal_cfg_values.h
  rz2_app_platform_cfg.h
  rz2_app_perfids.h
  rz2_app_msgids.h
  rz2_app_msgid_values.h
)

generate_configfile_set(${RZ2_APP_PLATFORM_CONFIG_FILE_LIST})
