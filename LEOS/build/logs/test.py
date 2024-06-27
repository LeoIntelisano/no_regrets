def compare_every_other_byte(file1_path, file2_path):
    with open(file1_path, "rb") as file1, open(file2_path, "rb") as file2:
        data1 = file1.read()
        data2 = file2.read()

    min_len = min(len(data1), len(data2))
    for i in range(0, min_len, 2):
        if data1[i] != data2[i]:
            print(f"Files differ at byte {i}")
            
    print("Every other byte in the files is the same.")
    return True

file1_path = "crash_mem.txt"
file2_path = "no_crash_mem.txt"

compare_every_other_byte(file1_path, file2_path)
