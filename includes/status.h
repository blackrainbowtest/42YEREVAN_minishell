/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:33:16 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/20 11:33:19 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATUS_H
# define STATUS_H

/**
 * @brief Get or set the last exit status of a command.
 *
 * This function encapsulates a static variable that stores the
 * exit status. It avoids using a global variable directly,
 * as required by the minishell subject.
 *
 * @param mode If 1, sets the status to new_value.
 *             If 0, returns the current status.
 * @param new_value The new status (used only if mode == 1).
 * @return The current stored status.
 */
int  last_status(int mode, int new_value);

#endif
