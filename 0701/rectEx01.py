def get_rect_area(w,h):
    return w*h

def main():
    width = float(input("Enter the width of the rectangle: "))
    height = float(input("Enter the height of the rectangle: "))
    area = get_rect_area(width, height)
    print(f"The area of the rectangle is: {area}")

if __name__ == "__main__": 
    main()

