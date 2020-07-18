Step1:: Install CZMQ 

commands :
`sudo apt-get update -y`
`sudo apt-get install -y rsyslog-czmq`

Reference [Link](https://zeromq.org/languages/c/)

Step2:: Install Open CV

sudo add-apt-repository ppa:lkoppel/opencv

sudo apt-get update

sudo apt install libopencv-calib3d3.2 libopencv-core3.2 libopencv-features2d3.2  libopencv-flann3.2 libopencv-highgui3.2 libopencv-imgcodecs3.2 libopencv-imgproc3.2 libopencv-ml3.2 libopencv-objdetect3.2 libopencv-photo3.2 libopencv-shape3.2 libopencv-stitching3.2 libopencv-superres3.2 libopencv-video3.2 libopencv-videoio3.2 libopencv-videostab3.2 libopencv-viz3.2 libopencv3.2-jni libopencv3.2-java libopencv-contrib3.2 

sudo apt install libopencv-calib3d-dev libopencv-core-dev libopencv-features2d-dev  libopencv-flann-dev libopencv-highgui-dev libopencv-imgcodecs-dev libopencv-imgproc-dev libopencv-ml-dev libopencv-objdetect-dev libopencv-photo-dev libopencv-shape-dev libopencv-stitching-dev libopencv-superres-dev libopencv-video-dev libopencv-videoio-dev libopencv-videostab-dev libopencv-viz-dev libopencv-contrib-dev libopencv-dev



Step3:: Download Code

Download code in [Link](https://github.com/KART-HIKEYAREKULAPALLI/VedioStreamZMQ)

Step4:: Compiling code

Make a new directory in the downloaded folder and apply `cmake` 

commands :
`mkdir build`
`cd build`
`cmake ..`
`make`

Step5:: Live Streaming

First Execute `my_program`  with command `./my_program` and then open your `Example.html` in Firefox
