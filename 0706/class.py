class Television:
    def __init__(self,channel,volume,on):  #생성자 , 변수 3개
        self.channel = channel # __channel (정석) 붙이면 외부에서 접근불가
        self.volume = volume
        self.on = on

    def set_channel(self,channel): # 채널 설정
        self.channel = channel

    def get_channel(self): # 채널 가져오기
        return self.channel
    
    def __str__(self): # 객체 출력
        return f"Television(channel={self.channel}, volume={self.volume}, on={self.on})"
    
    
tv1 = Television(1,29,True) # 객체 생성
tv2 = Television(2,20,False) # 객체 생성

print(tv1)
print(tv1.get_channel()) # tv1의 채널 가져오기 __channel로 생성시 사용법
print(tv1.channel) # tv1의 채널 가져오기 __channel로 생성시 사용불가



