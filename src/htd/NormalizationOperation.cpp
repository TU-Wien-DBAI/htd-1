/*
 * File:   NormalizationOperation.cpp
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

#ifndef HTD_HTD_NORMALIZATIONOPERATION_CPP
#define	HTD_HTD_NORMALIZATIONOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/NormalizationOperation.hpp>
#include <htd/SemiNormalizationOperation.hpp>
#include <htd/ExchangeNodeReplacementOperation.hpp>
#include <htd/LimitMaximumForgottenVertexCountOperation.hpp>
#include <htd/LimitMaximumIntroducedVertexCountOperation.hpp>

htd::NormalizationOperation::NormalizationOperation(void)
    : htd::SemiNormalizationOperation(), treatLeafNodesAsIntroduceNodes_(false)
{

}

htd::NormalizationOperation::NormalizationOperation(bool emptyRoot, bool emptyLeaves, bool identicalJoinNodeParent, bool treatLeafNodesAsIntroduceNodes)
    : htd::SemiNormalizationOperation(emptyRoot, emptyLeaves, identicalJoinNodeParent), treatLeafNodesAsIntroduceNodes_(treatLeafNodesAsIntroduceNodes)
{

}

htd::NormalizationOperation::~NormalizationOperation()
{

}

void htd::NormalizationOperation::apply(htd::IMutablePathDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::NormalizationOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices) const
{
    apply(decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>());
}

void htd::NormalizationOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    htd::SemiNormalizationOperation::apply(decomposition, labelingFunctions);

    htd::ExchangeNodeReplacementOperation exchangeNodeReplacementOperation;

    exchangeNodeReplacementOperation.setManagementInstance(managementInstance());

    exchangeNodeReplacementOperation.apply(decomposition, labelingFunctions);

    htd::LimitMaximumForgottenVertexCountOperation limitMaximumForgottenVertexCountOperation(1);

    limitMaximumForgottenVertexCountOperation.setManagementInstance(managementInstance());

    limitMaximumForgottenVertexCountOperation.apply(decomposition, labelingFunctions);

    htd::LimitMaximumIntroducedVertexCountOperation limitMaximumIntroducedVertexCountOperation(1);

    limitMaximumIntroducedVertexCountOperation.setManagementInstance(managementInstance());

    limitMaximumIntroducedVertexCountOperation.apply(decomposition, labelingFunctions);
}

void htd::NormalizationOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    htd::SemiNormalizationOperation::apply(decomposition, relevantVertices, labelingFunctions);

    htd::ExchangeNodeReplacementOperation exchangeNodeReplacementOperation;

    exchangeNodeReplacementOperation.setManagementInstance(managementInstance());

    exchangeNodeReplacementOperation.apply(decomposition, relevantVertices, labelingFunctions);

    htd::LimitMaximumForgottenVertexCountOperation limitMaximumForgottenVertexCountOperation(1);

    limitMaximumForgottenVertexCountOperation.setManagementInstance(managementInstance());

    limitMaximumForgottenVertexCountOperation.apply(decomposition, relevantVertices, labelingFunctions);

    htd::LimitMaximumIntroducedVertexCountOperation limitMaximumIntroducedVertexCountOperation(1);

    limitMaximumIntroducedVertexCountOperation.setManagementInstance(managementInstance());

    limitMaximumIntroducedVertexCountOperation.apply(decomposition, relevantVertices, labelingFunctions);
}

void htd::NormalizationOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::NormalizationOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

void htd::NormalizationOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    htd::SemiNormalizationOperation::apply(decomposition, labelingFunctions);

    htd::ExchangeNodeReplacementOperation exchangeNodeReplacementOperation;

    exchangeNodeReplacementOperation.setManagementInstance(managementInstance());

    exchangeNodeReplacementOperation.apply(decomposition, labelingFunctions);

    htd::LimitMaximumForgottenVertexCountOperation limitMaximumForgottenVertexCountOperation(1);

    limitMaximumForgottenVertexCountOperation.setManagementInstance(managementInstance());

    limitMaximumForgottenVertexCountOperation.apply(decomposition, labelingFunctions);

    htd::LimitMaximumIntroducedVertexCountOperation limitMaximumIntroducedVertexCountOperation(1, treatLeafNodesAsIntroduceNodes_);

    limitMaximumIntroducedVertexCountOperation.setManagementInstance(managementInstance());

    limitMaximumIntroducedVertexCountOperation.apply(decomposition, labelingFunctions);
}

void htd::NormalizationOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    std::size_t newVertexCount = 0;

    std::size_t oldCreatedVerticesCount = createdVertices.size();

    std::vector<htd::vertex_t> newRelevantVertices(relevantVertices.begin(), relevantVertices.end());

    htd::SemiNormalizationOperation::apply(decomposition, newRelevantVertices, labelingFunctions, createdVertices, removedVertices);

    newVertexCount = createdVertices.size() - oldCreatedVerticesCount;

    if (newVertexCount > 0)
    {
        std::copy(createdVertices.begin() + oldCreatedVerticesCount, createdVertices.end(), std::back_inserter(newRelevantVertices));

        oldCreatedVerticesCount = createdVertices.size();
    }

    htd::ExchangeNodeReplacementOperation exchangeNodeReplacementOperation;

    exchangeNodeReplacementOperation.setManagementInstance(managementInstance());

    exchangeNodeReplacementOperation.apply(decomposition, newRelevantVertices, labelingFunctions, createdVertices, removedVertices);

    newVertexCount = createdVertices.size() - oldCreatedVerticesCount;

    if (newVertexCount > 0)
    {
        std::copy(createdVertices.begin() + oldCreatedVerticesCount, createdVertices.end(), std::back_inserter(newRelevantVertices));

        oldCreatedVerticesCount = createdVertices.size();
    }

    htd::LimitMaximumForgottenVertexCountOperation limitMaximumForgottenVertexCountOperation(1);

    limitMaximumForgottenVertexCountOperation.setManagementInstance(managementInstance());

    limitMaximumForgottenVertexCountOperation.apply(decomposition, newRelevantVertices, labelingFunctions, createdVertices, removedVertices);

    newVertexCount = createdVertices.size() - oldCreatedVerticesCount;

    if (newVertexCount > 0)
    {
        std::copy(createdVertices.begin() + oldCreatedVerticesCount, createdVertices.end(), std::back_inserter(newRelevantVertices));

        oldCreatedVerticesCount = createdVertices.size();
    }

    htd::LimitMaximumIntroducedVertexCountOperation limitMaximumIntroducedVertexCountOperation(1, treatLeafNodesAsIntroduceNodes_);

    limitMaximumIntroducedVertexCountOperation.setManagementInstance(managementInstance());

    limitMaximumIntroducedVertexCountOperation.apply(decomposition, newRelevantVertices, labelingFunctions, createdVertices, removedVertices);
}

bool htd::NormalizationOperation::isLocalOperation(void) const
{
    return true;
}

bool htd::NormalizationOperation::createsTreeNodes(void) const
{
    return true;
}

bool htd::NormalizationOperation::removesTreeNodes(void) const
{
    return false;
}

bool htd::NormalizationOperation::modifiesBagContents(void) const
{
    return false;
}

bool htd::NormalizationOperation::createsSubsetMaximalBags(void) const
{
    return false;
}

bool htd::NormalizationOperation::createsLocationDependendLabels(void) const
{
    return false;
}

bool htd::NormalizationOperation::leafNodesTreatedAsIntroduceNodes(void) const
{
    return treatLeafNodesAsIntroduceNodes_;
}

htd::NormalizationOperation * htd::NormalizationOperation::clone(void) const
{
    htd::NormalizationOperation * ret = new htd::NormalizationOperation(emptyRootRequired(), emptyLeavesRequired(), identicalJoinNodeParentRequired(), treatLeafNodesAsIntroduceNodes_);

    ret->setManagementInstance(managementInstance());

    return ret;
}

#endif /* HTD_HTD_NORMALIZATIONOPERATION_CPP */
