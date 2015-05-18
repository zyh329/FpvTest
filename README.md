Run following command on Raspberry Pi (tested on Arch ARM Linux). Use your brain. (Don't forget to change the two 'host' sections in the command bellow and one 'host' section in fpv.cpp.)

/opt/vc/bin/raspivid -n -w 1296 -h 730 -b 6000000 -fps 49 -vf -hf -t 0 -pf high -o - | gst-launch-1.0 rtpbin name=rtpbin latency=60 drop-on-latency=true do-retransmission=true fdsrc do-timestamp=true ! h264parse ! rtph264pay config-interval=10 pt=96 ! rtprtxqueue ! rtpbin.send_rtp_sink_0 rtpbin.send_rtp_src_0 ! udpsink host=192.168.13.2 port=5000 rtpbin.send_rtcp_src_0 ! udpsink host=192.168.13.2 port=5001 sync=false async=false udpsrc port=5005 ! rtpbin.recv_rtcp_sink_0

For HUD test run on Rpi:

mavproxy.py  --baudrate 57600 --out 192.168.13.2:14550 --out 192.168.13.2:14560 --aircraft MyCopter
