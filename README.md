# AIX_2024
##AIX_2024 Project   
### Quantizatoin   
딥러닝에서 연산을 할 때 보통 부동소수점(FP32)를 이용한다.   
이를 최적화 하기위해 부동소수점(FP32)를 int8로 변환하는 것을 양자화(Quantization)이라고 한다.   
하지만 양자화를 하게되면 FP32 -> int8로 변환되는 과정에서 데이터의 Loss가 발생한다.      
