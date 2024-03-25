# AIX_2024
## AIX_2024 Project   
### Step.1 Advanced Quantizatoin   
딥러닝에서 연산을 할 때 보통 부동소수점(FP32)를 이용한다.   
이를 최적화 하기위해 부동소수점(FP32)를 int8로 변환하는 것을 양자화(Quantization)이라고 한다.   
하지만 양자화를 하게되면 FP32 -> int8로 변환되는 과정에서 데이터의 Loss가 발생한다.      
딥러닝을 통해 81.76% mAP의 정확도를 가지는 모델이 양자화를 통해 55.04%로 감소하는 문제점이 존재한다.   
이때 데이터의 Loss를 최소화 하기위한 알고리즘의 개발을 하고자 한다.  
##### (1) Layer 추가    
Quantization multiplier을 weight, input을 추가하여 mAP를 75%까지 개선했다.
```
float weight_quant_multiplier[TOTAL_CALIB_LAYER] = {
	16,	  //conv 0
     128,     //conv 2
     128,     //conv 4
     128,     //conv 6
     128,     //conv 8
     128,     //conv 10
     128,     //conv 12
     128,     //conv 13
     128,     //conv 14
     128,     //conv 17
     128};    //conv 20
	
float input_quant_multiplier[TOTAL_CALIB_LAYER] = {
	128,	  //conv 0
	   8,     //conv 2
	   8,     //conv 4
	   8,     //conv 6
	   8,     //conv 8
	   8,     //conv 10     
	   8,     //conv 12
	   8,     //conv 13
	   8,     //conv 14
	   8,     //conv 17
	   8};    //conv 20
```
##### (2) Layer parameter Calibration    
(1)에서 추가한 Layer의 Parameter은 임의로 설정한 값이다. 그리고 해당 parameter을 변경함에 따라 mAP와 time에 미약한 변화가 있음을 확인했다.   
mAP의 상승을 목표로 Layer의 적합한 parameter을 계산해서 적용하고자 한다.   
