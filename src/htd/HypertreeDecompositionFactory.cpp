/*
 * File:   HypertreeDecompositionFactory.cpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 *
 * Copyright 2015-2016, Michael Abseher
 *    E-Mail: <abseher@dbai.tuwien.ac.at>
 *
 * This file is part of htd.
 *
 * htd is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * htd is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
 * License for more details.

 * You should have received a copy of the GNU General Public License
 * along with htd.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef HTD_HTD_HYPERTREEDECOMPOSITIONFACTORY_CPP
#define HTD_HTD_HYPERTREEDECOMPOSITIONFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/HypertreeDecompositionFactory.hpp>
#include <htd/IMutableHypertreeDecomposition.hpp>
#include <htd/HypertreeDecomposition.hpp>
#include <htd/ITreeDecomposition.hpp>
#include <htd/Vertex.hpp>

#include <stdexcept>

htd::HypertreeDecompositionFactory::HypertreeDecompositionFactory(void)
{
    constructionTemplate_ = new htd::HypertreeDecomposition();
}

htd::HypertreeDecompositionFactory::~HypertreeDecompositionFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::HypertreeDecompositionFactory & htd::HypertreeDecompositionFactory::instance(void)
{
    static htd::HypertreeDecompositionFactory instance_;

    return instance_;
}

htd::IMutableHypertreeDecomposition * htd::HypertreeDecompositionFactory::getHypertreeDecomposition(void)
{
    return constructionTemplate_->clone();
}

htd::IMutableHypertreeDecomposition * htd::HypertreeDecompositionFactory::getHypertreeDecomposition(const htd::ITreeDecomposition & original)
{
    htd::IMutableHypertreeDecomposition * ret = constructionTemplate_->clone();

    *ret = original;

    return ret;
}

void htd::HypertreeDecompositionFactory::setConstructionTemplate(htd::IMutableHypertreeDecomposition * original)
{
    if (original == nullptr)
    {
        throw std::logic_error("void htd::HypertreeDecompositionFactory::setConstructionTemplate(htd::IMutableHypertreeDecomposition *)");
    }

    if (original->vertexCount() > 0)
    {
        throw std::logic_error("void htd::HypertreeDecompositionFactory::setConstructionTemplate(htd::IMutableHypertreeDecomposition *)");
    }

    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }

    constructionTemplate_ = original;
}

htd::IMutableHypertreeDecomposition & htd::HypertreeDecompositionFactory::accessMutableHypertreeDecomposition(htd::IHypertreeDecomposition & original)
{
    return *(dynamic_cast<htd::IMutableHypertreeDecomposition *>(&original));
}

const htd::IMutableHypertreeDecomposition & htd::HypertreeDecompositionFactory::accessMutableHypertreeDecomposition(const htd::IHypertreeDecomposition & original)
{
    return *(dynamic_cast<const htd::IMutableHypertreeDecomposition *>(&original));
}

#endif /* HTD_HTD_HYPERTREEDECOMPOSITIONFACTORY_CPP */
