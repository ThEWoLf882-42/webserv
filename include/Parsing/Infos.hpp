/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Infos.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:34:15 by mel-moun          #+#    #+#             */
/*   Updated: 2024/02/13 16:57:23 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <webserv.hpp>

namespace wbs
{
    class Infos
    {
    public:
        std::map<std::string, std::vector<std::string> > directives;
        std::vector<Location> locations;

    public:
        Infos();
        Infos(const Infos& ob);
        Infos& operator=(const Infos& ob);
        ~Infos();

        void    print_directives();
        void    end_map(std::map<std::string, std::vector<std::string> >& map);
    };
}
