package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

const (
	SHELVESPERVERTICALSECTION = 5
	VERTICALSECTIONCOUNT      = 1
	TOTALITEMSTORAGE          = 1500
	STORAGEZONECOUNT          = 10
	SHELVESPERZONE            = 3
	SLOTSTORAGE               = 10
)

type Address [4]int
type Storage map[Address]map[string]int

func main() {
	storage := make(Storage)
	reader := bufio.NewReader(os.Stdin)

	fmt.Println("Для добавления предмета воспользуйтесь командой ADD (ADD <название> <количество> <ячейка>)")
	fmt.Println("Для удаления предмета воспользуйтесь командой REMOVE (REMOVE <название> <количество> <ячейка>)")
	fmt.Println("Для получения информации о складе воспользуйтесь командой INFO")
	fmt.Println("Для выхода из программы воспользуйтесь командой EXIT")

	for {
		fmt.Print("Введите команду: ")
		input, _ := reader.ReadString('\n')
		commandParts := strings.Fields(strings.TrimSpace(input))

		if len(commandParts) == 0 {
			continue
		}

		command := strings.ToUpper(commandParts[0])

		switch command {
		case "ADD", "REMOVE":
			for {
				fmt.Print("Введите <название> <кол-во> <ячейка>: ")
				line, _ := reader.ReadString('\n')
				parts := strings.Fields(strings.TrimSpace(line))
				if len(parts) != 3 {
					fmt.Println("Некорректный ввод. Попробуйте еще раз.")
					continue
				}

				itemName := parts[0]
				items, err := strconv.Atoi(parts[1])
				sectionCode := parts[2]
				if err != nil {
					fmt.Println("Количество должно быть числом.")
					continue
				}
				if len(sectionCode) != 4 {
					fmt.Println("Код ячейки должен быть из 4 символов.")
					continue
				}

				zone := sectionCode[0]
				section := int(sectionCode[1] - '0')
				vertical := int(sectionCode[2] - '0')
				shelf := int(sectionCode[3] - '0')

				if !validateInput(command, itemName, items, zone, section, vertical, shelf, sectionCode, storage) {
					continue
				}

				addr := Address{int(zone - 'A'), section, vertical, shelf}

				if command == "ADD" {
					if storage[addr] != nil && storage[addr][itemName]+items > SLOTSTORAGE || items > SLOTSTORAGE {
						fmt.Println("Недостаточно места на складе. Максимум в ячейке:", SLOTSTORAGE)
						continue
					}
					ADD(storage, addr, itemName, items)
				} else {
					if storage[addr] == nil || storage[addr][itemName] < items {
						fmt.Println("Недостаточно предметов на складе или предмет отсутствует.")
						continue
					}
					REMOVE(storage, addr, itemName, items)
				}
				break
			}
		case "INFO":
			INFO(storage)
		case "EXIT":
			return
		default:
			fmt.Println("Неизвестная команда. Попробуйте еще раз.")
		}
		fmt.Println("----------------------------------------")
	}
}

func validateInput(command, itemName string, items int, zone byte, section, vertical, shelf int, code string, storage Storage) bool {
	if zone < 'A' || zone > 'A'+STORAGEZONECOUNT-1 {
		fmt.Printf("Некорректная зона. Зона должна быть от A до %c\n", 'A'+STORAGEZONECOUNT-1)
		return false
	}
	if section < 1 || section > SHELVESPERZONE {
		fmt.Printf("Некорректная секция. Должна быть от 1 до %d\n", SHELVESPERZONE)
		return false
	}
	if vertical < 1 || vertical > VERTICALSECTIONCOUNT {
		fmt.Printf("Некорректная вертикальная секция. Должна быть от 1 до %d\n", VERTICALSECTIONCOUNT)
		return false
	}
	if shelf < 1 || shelf > SHELVESPERVERTICALSECTION {
		fmt.Printf("Некорректная полка. Должна быть от 1 до %d\n", SHELVESPERVERTICALSECTION)
		return false
	}
	if items <= 0 {
		fmt.Println("Количество должно быть больше 0.")
		return false
	}
	if len(code) != 4 {
		fmt.Println("Код ячейки должен быть длиной 4 символа.")
		return false
	}
	return true
}

func ADD(storage Storage, address Address, itemName string, items int) {
	if _, exists := storage[address]; !exists {
		storage[address] = make(map[string]int)
	}
	storage[address][itemName] += items
	fmt.Printf("Добавлено %d предметов %s в ячейку %c%d%d%d\n",
		items, itemName, address[0]+'A', address[1], address[2], address[3])
}

func REMOVE(storage Storage, address Address, itemName string, items int) {
	storage[address][itemName] -= items
	fmt.Printf("Удалено %d предметов %s из ячейки %c%d%d%d\n",
		items, itemName, address[0]+'A', address[1], address[2], address[3])
}

func INFO(storage Storage) {
	fmt.Println("Информация о складе:")
	totalItems := 0
	storageLoad := make([]int, STORAGEZONECOUNT)

	for addr, itemsMap := range storage {
		for item, count := range itemsMap {
			fmt.Printf("Зона: %c, Секция: %d, Вертикальная секция: %d, Полка: %d, Предмет: %s, Количество: %d\n",
				addr[0]+'A', addr[1], addr[2], addr[3], item, count)
			totalItems += count
			storageLoad[addr[0]] += count
		}
	}

	fmt.Println("Загрузка склада по зонам:")
	for i, count := range storageLoad {
		fmt.Printf("Зона %c: %d\n", 'A'+i, count)
	}
	fmt.Printf("Общее количество предметов на складе: %d\n", totalItems)
}
