<?php
/**
 * @file
 * simple_card.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function simple_card_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function simple_card_node_info() {
  $items = array(
    'card' => array(
      'name' => t('Card'),
      'base' => 'node_content',
      'description' => t('Thumbnail Title and Blurb linked description of an Article or other content. May be internal or external content. For use in NewsLetter, and Deck and Collection Builders.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
