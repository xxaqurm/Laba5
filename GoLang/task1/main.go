package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Address [4]int

type Storage map[Address]map[string]int

const (
	ShelvesPerVerticalSection = 5
	VerticalSectionCount      = 1
	TotalItemStorage          = 1500
	StorageZoneCount          = 10
	ShelvesPerZone            = 3
	SlotStorage               = 10
)

func validateInput(itemName string, items int, zone rune, section, verticalSection, shelf int, sectionCode string) bool {
	if zone < 'A' || zone > 'A'+rune(StorageZoneCount)-1 {
		fmt.Printf("Некорректная зона. Зона должна быть от A до %c\n", 'A'+StorageZoneCount-1)
		return false
	} else if section < 1 || section > ShelvesPerZone {
		fmt.Printf("Некорректный номер секции. Секция должна быть от 1 до %d\n", ShelvesPerZone)
		return false
	} else if verticalSection < 1 || verticalSection > VerticalSectionCount {
		fmt.Printf("Некорректный номер вертикальной секции. Вертикальная секция должна быть от 1 до %d\n", VerticalSectionCount)
		return false
	} else if shelf < 1 || shelf > ShelvesPerVerticalSection {
		fmt.Printf("Некорректный номер полки. Полка должна быть от 1 до %d\n", ShelvesPerVerticalSection)
		return false
	} else if items <= 0 {
		fmt.Println("Некорректное количество предметов. Количество должно быть больше 0.")
		return false
	} else if len(sectionCode) != 4 {
		fmt.Println("Некорректный код секции. Код секции должен состоять из 4 символов.")
		return false
	}
	return true
}

func info(storage Storage) {
	totalItems := 0
	storageLoad := make([]int, StorageZoneCount)
	fmt.Println("Информация о складе:")
	for addr, itemsMap := range storage {
		zoneIndex := addr[0]
		for name, count := range itemsMap {
			fmt.Printf("Зона: %c, Секция: %d, Вертикальная секция: %d, Полка: %d, Предмет: %s, Количество: %d\n",
				'A'+zoneIndex, addr[1], addr[2], addr[3], name, count)
			totalItems += count
			storageLoad[zoneIndex] += count
		}
	}
	fmt.Println("Загрузка склада по зонам:")
	for i, load := range storageLoad {
		fmt.Printf("Зона %c: %d\n", 'A'+i, load)
	}
	fmt.Printf("Общее количество предметов на складе: %d\n", totalItems)
}

func add(storage Storage, address Address, itemName string, items int) {
	if storage[address] == nil {
		storage[address] = make(map[string]int)
	}
	storage[address][itemName] += items
	fmt.Printf("Добавлено %d предметов %s в ячейку %c%d%d%d\n", items, itemName, 'A'+address[0], address[1], address[2], address[3])
}

func remove(storage Storage, address Address, itemName string, items int) {
	storage[address][itemName] -= items
	fmt.Printf("Удалено %d предметов %s из ячейки %c%d%d%d\n", items, itemName, 'A'+address[0], address[1], address[2], address[3])
}

func main() {
	storage := make(Storage)
	scanner := bufio.NewScanner(os.Stdin)
	fmt.Println("ADD <название> <кол-во> <ячейка>, REMOVE, INFO, EXIT")

	for {
		fmt.Print("Введите команду: ")
		if !scanner.Scan() {
			break
		}
		input := scanner.Text()
		parts := strings.Fields(input)
		if len(parts) == 0 {
			continue
		}
		command := parts[0]
		switch command {
		case "ADD", "REMOVE":
			if len(parts) != 4 {
				fmt.Println("Неверный формат команды. Пример: ADD Orange 3 A112")
				continue
			}
			itemName := parts[1]
			items, err := strconv.Atoi(parts[2])
			if err != nil {
				fmt.Println("Некорректное количество.")
				continue
			}
			sectionCode := parts[3]
			zone := rune(sectionCode[0])
			section := int(sectionCode[1] - '0')
			vertical := int(sectionCode[2] - '0')
			shelf := int(sectionCode[3] - '0')
			if !validateInput(itemName, items, zone, section, vertical, shelf, sectionCode) {
				continue
			}
			address := Address{int(zone - 'A'), section, vertical, shelf}
			if command == "ADD" {
				if storage[address][itemName]+items > SlotStorage {
					fmt.Println("Недостаточно места в ячейке. Максимум 10.")
					continue
				}
				add(storage, address, itemName, items)
			} else {
				if count, ok := storage[address][itemName]; !ok || count < items {
					fmt.Println("Недостаточно предметов или предмет не найден.")
					continue
				}
				remove(storage, address, itemName, items)
			}
		case "INFO":
			info(storage)
		case "EXIT":
			return
		default:
			fmt.Println("Неизвестная команда.")
		}
		fmt.Println("----------------------------------------")
	}
}
