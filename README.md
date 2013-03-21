This will be ground station software for a quadrotor or any other aerial vehicle.
For now it consists of a window with Gstreamer's video output overlayed with
some initial HUD implementation.

On the vehicle pipeline similar to this should be run:
(you can run this actual command)
gst-launch-0.10 gstrtpbin name=rtpbin latency=10 v4l2src ! image/jpeg,width=320,height=240,framerate=\(fraction\)30/1 ! rtpjpegpay quality=40 ! rtpbin.send_rtp_sink_0 rtpbin.send_rtp_src_0 ! udpsink host=192.168.3.2 port=5000 rtpbin.send_rtcp_src_0 ! udpsink host=192.168.3.2 port=5001 sync=false async=false udpsrc port=5005 ! rtpbin.recv_rtcp_sink_0
(Edit IP addresses according to your situation!!!)

QuadGCS implements pipeline similar to this:
(you should run QuadGCS instead of this command)
gst-launch-0.10 -v gstrtpbin name=rtpbin latency=5 udpsrc caps="application/x-rtp,media=(string)video,clock-rate=(int)90000" port=5000 ! rtpbin.recv_rtp_sink_0 rtpbin. ! rtpjpegdepay ! jpegdec ! xvimagesink sync=false udpsrc port=5001 ! rtpbin.recv_rtcp_sink_0 rtpbin.send_rtcp_src_0 ! udpsink host=192.168.3.1 port=5005 sync=false async=false
(IP addresses are just hardcoded to source so far so you may need to edit the fpv.cpp)
