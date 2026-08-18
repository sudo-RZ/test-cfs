###########################################################
#
# RZ1_APP platform build setup
#
# This file is evaluated as part of the "prepare" stage
# and can be used to set up prerequisites for the build,
# such as generating header files
#
###########################################################

# The list of header files that control the RZ1_APP configuration
set(RZ1_APP_PLATFORM_CONFIG_FILE_LIST
  rz1_app_internal_cfg_values.h
  rz1_app_platform_cfg.h
  rz1_app_perfids.h
  rz1_app_msgids.h
  rz1_app_msgid_values.h
)

generate_configfile_set(${RZ1_APP_PLATFORM_CONFIG_FILE_LIST})
