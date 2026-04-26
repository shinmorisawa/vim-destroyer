import csv

# configuration
INPUT_FILE = 'lut/cie_1931_2deg.csv'
STRUCT_NAME = 'cie_1931_2deg_1nm'
START_WAVELENGTH = 360
END_WAVELENGTH = 830
STEP = 1

def generate_c_header(data):
    print(f"static const CMFEntry {STRUCT_NAME}[] = {{")
    
    for row in data:
        w, x, y, z = row
        print(f"    {{ {x:.12f}, {y:.12f}, {z:.12f} }}, // {int(w)}nm")
        
    print("};")

def parse_csv(filename):
    cmf_data = []
    try:
        with open(filename, mode='r') as f:
            reader = csv.reader(f)
            for row in reader:
                # skip headers or empty rows
                try:
                    w = float(row[0])
                    # only grab the intervals we want (e.g., every 5nm)
                    if w >= START_WAVELENGTH and w <= END_WAVELENGTH and w % STEP == 0:
                        cmf_data.append([w, float(row[1]), float(row[2]), float(row[3])])
                except (ValueError, IndexError):
                    continue
    except FileNotFoundError:
        print(f"/* error: {filename} not found */")
        return []
    
    return cmf_data

if __name__ == "__main__":
    data = parse_csv(INPUT_FILE)
    if data:
        generate_c_header(data)
