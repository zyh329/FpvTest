#-------------------------------------------------
#
# Project created by QtCreator 2015-03-16T00:11:54
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FpvTest
TEMPLATE = app

CONFIG += c++11
CONFIG += link_pkgconfig
PKGCONFIG += Qt5GLib-2.0 Qt5GStreamer-1.0 Qt5GStreamerUi-1.0 Qt5GStreamerUtils-1.0

SOURCES += main.cpp\
        mainwindow.cpp \
    quadgcs.cpp \
    hud.cpp \
    fpv.cpp

HEADERS  += mainwindow.h \
    hud.h \
    fpv.h \
    quadgcs.h \
    mavlink/ardupilotmega/ardupilotmega.h \
    mavlink/ardupilotmega/mavlink.h \
    mavlink/ardupilotmega/mavlink_msg_ahrs.h \
    mavlink/ardupilotmega/mavlink_msg_ahrs2.h \
    mavlink/ardupilotmega/mavlink_msg_ahrs3.h \
    mavlink/ardupilotmega/mavlink_msg_airspeed_autocal.h \
    mavlink/ardupilotmega/mavlink_msg_ap_adc.h \
    mavlink/ardupilotmega/mavlink_msg_autopilot_version_request.h \
    mavlink/ardupilotmega/mavlink_msg_battery2.h \
    mavlink/ardupilotmega/mavlink_msg_camera_feedback.h \
    mavlink/ardupilotmega/mavlink_msg_camera_status.h \
    mavlink/ardupilotmega/mavlink_msg_compassmot_status.h \
    mavlink/ardupilotmega/mavlink_msg_data16.h \
    mavlink/ardupilotmega/mavlink_msg_data32.h \
    mavlink/ardupilotmega/mavlink_msg_data64.h \
    mavlink/ardupilotmega/mavlink_msg_data96.h \
    mavlink/ardupilotmega/mavlink_msg_digicam_configure.h \
    mavlink/ardupilotmega/mavlink_msg_digicam_control.h \
    mavlink/ardupilotmega/mavlink_msg_fence_fetch_point.h \
    mavlink/ardupilotmega/mavlink_msg_fence_point.h \
    mavlink/ardupilotmega/mavlink_msg_fence_status.h \
    mavlink/ardupilotmega/mavlink_msg_gimbal_control.h \
    mavlink/ardupilotmega/mavlink_msg_gimbal_report.h \
    mavlink/ardupilotmega/mavlink_msg_hwstatus.h \
    mavlink/ardupilotmega/mavlink_msg_led_control.h \
    mavlink/ardupilotmega/mavlink_msg_limits_status.h \
    mavlink/ardupilotmega/mavlink_msg_meminfo.h \
    mavlink/ardupilotmega/mavlink_msg_mount_configure.h \
    mavlink/ardupilotmega/mavlink_msg_mount_control.h \
    mavlink/ardupilotmega/mavlink_msg_mount_status.h \
    mavlink/ardupilotmega/mavlink_msg_radio.h \
    mavlink/ardupilotmega/mavlink_msg_rally_fetch_point.h \
    mavlink/ardupilotmega/mavlink_msg_rally_point.h \
    mavlink/ardupilotmega/mavlink_msg_rangefinder.h \
    mavlink/ardupilotmega/mavlink_msg_sensor_offsets.h \
    mavlink/ardupilotmega/mavlink_msg_set_mag_offsets.h \
    mavlink/ardupilotmega/mavlink_msg_simstate.h \
    mavlink/ardupilotmega/mavlink_msg_wind.h \
    mavlink/ardupilotmega/testsuite.h \
    mavlink/ardupilotmega/version.h \
    mavlink/common/common.h \
    mavlink/common/mavlink.h \
    mavlink/common/mavlink_msg_actuator_control_target.h \
    mavlink/common/mavlink_msg_att_pos_mocap.h \
    mavlink/common/mavlink_msg_attitude.h \
    mavlink/common/mavlink_msg_attitude_quaternion.h \
    mavlink/common/mavlink_msg_attitude_quaternion_cov.h \
    mavlink/common/mavlink_msg_attitude_target.h \
    mavlink/common/mavlink_msg_auth_key.h \
    mavlink/common/mavlink_msg_autopilot_version.h \
    mavlink/common/mavlink_msg_battery_status.h \
    mavlink/common/mavlink_msg_change_operator_control.h \
    mavlink/common/mavlink_msg_change_operator_control_ack.h \
    mavlink/common/mavlink_msg_command_ack.h \
    mavlink/common/mavlink_msg_command_int.h \
    mavlink/common/mavlink_msg_command_long.h \
    mavlink/common/mavlink_msg_data_stream.h \
    mavlink/common/mavlink_msg_data_transmission_handshake.h \
    mavlink/common/mavlink_msg_debug.h \
    mavlink/common/mavlink_msg_debug_vect.h \
    mavlink/common/mavlink_msg_distance_sensor.h \
    mavlink/common/mavlink_msg_encapsulated_data.h \
    mavlink/common/mavlink_msg_file_transfer_protocol.h \
    mavlink/common/mavlink_msg_global_position_int.h \
    mavlink/common/mavlink_msg_global_position_int_cov.h \
    mavlink/common/mavlink_msg_global_vision_position_estimate.h \
    mavlink/common/mavlink_msg_gps2_raw.h \
    mavlink/common/mavlink_msg_gps2_rtk.h \
    mavlink/common/mavlink_msg_gps_global_origin.h \
    mavlink/common/mavlink_msg_gps_inject_data.h \
    mavlink/common/mavlink_msg_gps_raw_int.h \
    mavlink/common/mavlink_msg_gps_rtk.h \
    mavlink/common/mavlink_msg_gps_status.h \
    mavlink/common/mavlink_msg_heartbeat.h \
    mavlink/common/mavlink_msg_highres_imu.h \
    mavlink/common/mavlink_msg_hil_controls.h \
    mavlink/common/mavlink_msg_hil_gps.h \
    mavlink/common/mavlink_msg_hil_optical_flow.h \
    mavlink/common/mavlink_msg_hil_rc_inputs_raw.h \
    mavlink/common/mavlink_msg_hil_sensor.h \
    mavlink/common/mavlink_msg_hil_state.h \
    mavlink/common/mavlink_msg_hil_state_quaternion.h \
    mavlink/common/mavlink_msg_local_position_ned.h \
    mavlink/common/mavlink_msg_local_position_ned_cov.h \
    mavlink/common/mavlink_msg_local_position_ned_system_global_offset.h \
    mavlink/common/mavlink_msg_log_data.h \
    mavlink/common/mavlink_msg_log_entry.h \
    mavlink/common/mavlink_msg_log_erase.h \
    mavlink/common/mavlink_msg_log_request_data.h \
    mavlink/common/mavlink_msg_log_request_end.h \
    mavlink/common/mavlink_msg_log_request_list.h \
    mavlink/common/mavlink_msg_manual_control.h \
    mavlink/common/mavlink_msg_manual_setpoint.h \
    mavlink/common/mavlink_msg_memory_vect.h \
    mavlink/common/mavlink_msg_mission_ack.h \
    mavlink/common/mavlink_msg_mission_clear_all.h \
    mavlink/common/mavlink_msg_mission_count.h \
    mavlink/common/mavlink_msg_mission_current.h \
    mavlink/common/mavlink_msg_mission_item.h \
    mavlink/common/mavlink_msg_mission_item_int.h \
    mavlink/common/mavlink_msg_mission_item_reached.h \
    mavlink/common/mavlink_msg_mission_request.h \
    mavlink/common/mavlink_msg_mission_request_list.h \
    mavlink/common/mavlink_msg_mission_request_partial_list.h \
    mavlink/common/mavlink_msg_mission_set_current.h \
    mavlink/common/mavlink_msg_mission_write_partial_list.h \
    mavlink/common/mavlink_msg_named_value_float.h \
    mavlink/common/mavlink_msg_named_value_int.h \
    mavlink/common/mavlink_msg_nav_controller_output.h \
    mavlink/common/mavlink_msg_optical_flow.h \
    mavlink/common/mavlink_msg_optical_flow_rad.h \
    mavlink/common/mavlink_msg_param_map_rc.h \
    mavlink/common/mavlink_msg_param_request_list.h \
    mavlink/common/mavlink_msg_param_request_read.h \
    mavlink/common/mavlink_msg_param_set.h \
    mavlink/common/mavlink_msg_param_value.h \
    mavlink/common/mavlink_msg_ping.h \
    mavlink/common/mavlink_msg_position_target_global_int.h \
    mavlink/common/mavlink_msg_position_target_local_ned.h \
    mavlink/common/mavlink_msg_power_status.h \
    mavlink/common/mavlink_msg_radio_status.h \
    mavlink/common/mavlink_msg_raw_imu.h \
    mavlink/common/mavlink_msg_raw_pressure.h \
    mavlink/common/mavlink_msg_rc_channels.h \
    mavlink/common/mavlink_msg_rc_channels_override.h \
    mavlink/common/mavlink_msg_rc_channels_raw.h \
    mavlink/common/mavlink_msg_rc_channels_scaled.h \
    mavlink/common/mavlink_msg_request_data_stream.h \
    mavlink/common/mavlink_msg_safety_allowed_area.h \
    mavlink/common/mavlink_msg_safety_set_allowed_area.h \
    mavlink/common/mavlink_msg_scaled_imu.h \
    mavlink/common/mavlink_msg_scaled_imu2.h \
    mavlink/common/mavlink_msg_scaled_imu3.h \
    mavlink/common/mavlink_msg_scaled_pressure.h \
    mavlink/common/mavlink_msg_scaled_pressure2.h \
    mavlink/common/mavlink_msg_serial_control.h \
    mavlink/common/mavlink_msg_servo_output_raw.h \
    mavlink/common/mavlink_msg_set_actuator_control_target.h \
    mavlink/common/mavlink_msg_set_attitude_target.h \
    mavlink/common/mavlink_msg_set_gps_global_origin.h \
    mavlink/common/mavlink_msg_set_mode.h \
    mavlink/common/mavlink_msg_set_position_target_global_int.h \
    mavlink/common/mavlink_msg_set_position_target_local_ned.h \
    mavlink/common/mavlink_msg_sim_state.h \
    mavlink/common/mavlink_msg_statustext.h \
    mavlink/common/mavlink_msg_sys_status.h \
    mavlink/common/mavlink_msg_system_time.h \
    mavlink/common/mavlink_msg_terrain_check.h \
    mavlink/common/mavlink_msg_terrain_data.h \
    mavlink/common/mavlink_msg_terrain_report.h \
    mavlink/common/mavlink_msg_terrain_request.h \
    mavlink/common/mavlink_msg_timesync.h \
    mavlink/common/mavlink_msg_v2_extension.h \
    mavlink/common/mavlink_msg_vfr_hud.h \
    mavlink/common/mavlink_msg_vicon_position_estimate.h \
    mavlink/common/mavlink_msg_vision_position_estimate.h \
    mavlink/common/mavlink_msg_vision_speed_estimate.h \
    mavlink/common/testsuite.h \
    mavlink/common/version.h \
    mavlink/checksum.h \
    mavlink/mavlink_conversions.h \
    mavlink/mavlink_helpers.h \
    mavlink/mavlink_types.h \
    mavlink/protocol.h

FORMS    += mainwindow.ui

DISTFILES += \
    FpvTest.pro.user
