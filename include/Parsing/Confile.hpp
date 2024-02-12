/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Confile.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimi <agimi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:35:14 by mel-moun          #+#    #+#             */
/*   Updated: 2024/02/12 10:31:47 by agimi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFILE_HPP
#define CONFILE_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

#include "Location.hpp"

class Confile
{
private:
    std::map<std::string, std::vector<std::string> > directives;
    std::vector<Location> locations;

    std::ifstream infile;
    std::string input;

public:
    Confile();
    Confile(const std::string &file);
    Confile &operator=(const Confile &ob);
    Confile(const Confile &ob);
    ~Confile();

    // Main parsing
    void parsing();

    // Main parsing' functions
    void closed_brackets();

    // Print content of directives attribute
    void print_directives();

    // Parse
    std::vector<Confile> parse();
    void syntax_error();

    const std::string take_path(const std::string &input, const std::string &key);
    void check_semicolon(std::vector<Confile> &servers);
    void end_map(std::map<std::string, std::vector<std::string> > &map);
    void count_semicolons(const std::string &str, int i);
};

#endif
