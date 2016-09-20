<?php
/**
 * @file
 * simple_card.ajax.inc
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function simple_card_form_card_node_form_alter(&$form, &$form_state, $form_id) {

  $form['field_content'][LANGUAGE_NONE][0]['target_id']['#ajax'] = array(
      'callback' => 'simple_card_overrides',
      'event' => 'autocompleteSelect',
      'wrapper' => 'card_form',
    );
  // Wrap the title field
   $form['#prefix'] = '<div id="card_form">';
   $form['#suffix'] = '</div>';

  if (!empty($form_state['values']['field_content'][LANGUAGE_NONE][0]['target_id'])) {
    // Load the node from target_id.
    unset($form_state['input']['title']);
    unset($form_state['input']['field_blurb_override']);
    unset($form_state['input']['field_image_override']);
    unset($form_state['input']['field_link_override']);

    $target_node = node_load($form_state['values']['field_content'][LANGUAGE_NONE][0]['target_id']);
    $form['title']['#default_value'] = $target_node->title;

    // Set Blurb.
    $blurb = '';
    if (!empty($target_node->body[LANGUAGE_NONE][0]['summary'])){
      $blurb = $target_node->body[LANGUAGE_NONE][0]['summary'];
    }
    $form['field_blurb_override'][LANGUAGE_NONE][0]['#default_value'] = $blurb;

    // Set image.
    $form['field_image_override'][LANGUAGE_NONE][0]['#default_value']['fid'] = $target_node->field_image_homepage_story[LANGUAGE_NONE][0]['fid'];

    // Set link.
    // TODO: use url() with ABSOLUTE once we get that working again.
    $link_value = 'http://greatist.com/' . drupal_get_path_alias('node/' . $target_node->nid);

    $form['field_link_override'][LANGUAGE_NONE][0]['#default_value']['url'] = $link_value;
  }

  // Disable wysiwyg on body
  $form['field_blurb_override'][LANGUAGE_NONE][0]['#wysiwyg'] = FALSE;
  $form['field_blurb_override'][LANGUAGE_NONE][0]['#format'] = 'plain_text';
  $form['field_blurb_override'][LANGUAGE_NONE][0]['#rows'] = 5;

  //dpm($form,'form card');
  //dpm($form_state,'form_state card');
  return $form;
}

/**
 * Implements hook_node_prepare().
 */
function simple_card_node_prepare($node) {
  if (empty($node->nid) && !isset($node->path['pathauto']) && in_array($node->type, array('card'))) {
    // Default the Pathauto checkbox to be unchecked for new page nodes.
    $node->path['pathauto'] = FALSE;
  }
}

function simple_card_overrides(&$form, $form_state) {

  return $form;
}

