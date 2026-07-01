class Television:
    def __init__(self, channel, volume, on):
        self.channel = channel
        self.volume = volume
        self.on = on
    
    def show(self):
        print(f"Channel: {self.channel} Volume: {self.volume} On: {self.on}")

    def set_channel(self, channel):
        self.channel = channel
    
    def get_channel(self):
        return self.channel
    
tv1 = Television(1, 10, True)
print(tv1)
tv1.show()
s

