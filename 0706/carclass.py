class Car:
    def __init__(self, make, model, color, price):
        self.make = make
        self.model = model
        self.color = color
        self.price = price

    def set_make(self, make):
        self.make = make

    def get_make(self):
        return self.make
    
    def __str__(self):
        return f"Car(make={self.make}, model={self.model}, color={self.color}, price={self.price})"
    
class ElectricCar(Car): # 상속
    def __init__(self, make, model, color, price, battery_capacity):
        super().__init__(make, model, color, price)  # super()를 사용하여 부모 클래스의 생성자 호출
        self.battery_capacity = battery_capacity

    def set_battery_capacity(self,battery_capacity):
        self.battery_capacity = battery_capacity

    def get_battery_capacity(self):
        return self.battery_capacity
    
    def __str__(self):
        return f"ElectricCar(make={self.make}, model={self.model}, color={self.color}, price={self.price}, battery_capacity={self.battery_capacity})"
    

myCar = ElectricCar("Tesla", "Model S", "Red", 79999, 100)
print(myCar)


