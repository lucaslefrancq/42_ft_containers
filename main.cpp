/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:24:20 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/17 09:34:20 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers/vector.hpp"
#include "containers/list.hpp"
#include "containers/stack.hpp"
#include "containers/queue.hpp"
#include "containers/map.hpp"
#include "templates/stl_like.hpp"

#include "../42_Containator/includes_and_utils/print_type.hpp"

#include <iostream>
#include <string>

#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>

int main()
{

	{
		ft::map<int, std::string> x;

		ft::pair<int, std::string> pa1(58966, "hello coco"); // penser a regler le probleme de la pair
		// ft::pair<int, char> pa2(2, 'a'); // penser a regler le probleme de la pair
		// ft::pair<int, char> pa3(0, 'p'); // penser a regler le probleme de la pair
		// ft::pair<int, char> pa4(4, 'z'); // penser a regler le probleme de la pair
		// ft::pair<int, char> pa5(8, 'z'); // penser a regler le probleme de la pair
		// ft::pair<int, char> pa6(-4, 'z'); // penser a regler le probleme de la pair
		// ft::pair<int, char> pa7(3, 'z'); // penser a regler le probleme de la pair
		// ft::pair<int, char> pa8(5, 'z'); // penser a regler le probleme de la pair
		x.insert(pa1);
		// x.insert(pa2);
		// x.insert(pa3);
		// x.insert(pa4);
		// x.insert(pa5);
		// x.insert(pa6);
		// x.insert(pa7);
		// x.insert(pa8);
		ft::map<int, std::string> tmp = x;
		std::cout << "size before modif: " << tmp.size()<< "\n";

		for (ft::map<int, std::string>::const_iterator it = x.begin(); it != x.end(); ++it)
			std::cout << "[" << x[it->first] << "] | ";
		std::cout << "\n";

		ft::map<int, std::string> tmp2;
		for (ft::map<int, std::string>::const_iterator it = x.begin(); it != x.end(); ++it)
		{
			std::cerr << "first = " << it->first << " and second = " << it->second << "\n";
			tmp2[it->first] = it->second;
			std::cerr << "first = " << it->first << " and second = " << it->second << "\n";
		}
		std::cout << "\nsize after operator[]: " << tmp.size() << "\n";
	}

	return (0);
}