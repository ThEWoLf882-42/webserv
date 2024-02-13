/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:15:55 by mel-moun          #+#    #+#             */
/*   Updated: 2024/02/13 16:31:43 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <webserv.hpp>

namespace wbs
{
    class Location
    {
    public:
        std::string path;
        std::map<std::string, std::vector<std::string> > params;

    public:
        Location();
        Location(const Location &ob);
        Location &operator=(const Location &ob);
        ~Location();

        void end_map_location(std::map<std::string, std::vector<std::string> > &map);
    };
}