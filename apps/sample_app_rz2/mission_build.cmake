###########################################################
#
# RZ2_APP mission build setup
#
# This file is evaluated as part of the "prepare" stage
# and can be used to set up prerequisites for the build,
# such as generating header files
#
###########################################################

# The list of header files that control the RZ2_APP configuration
set(RZ2_APP_MISSION_CONFIG_FILE_LIST
  rz2_app_fcncode_values.h
  rz2_app_interface_cfg_values.h
  rz2_app_mission_cfg.h
  rz2_app_perfids.h
  rz2_app_msg.h
  rz2_app_msgdefs.h
  rz2_app_msgstruct.h
  rz2_app_tbl.h
  rz2_app_tbldefs.h
  rz2_app_tblstruct.h
  rz2_app_topicid_values.h
)

generate_configfile_set(${RZ2_APP_MISSION_CONFIG_FILE_LIST})

